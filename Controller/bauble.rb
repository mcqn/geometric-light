# Bauble class
# (c) Copyright 2017 MCQN Ltd

class Bauble
  PatternOff = 1

  attr_accessor :teensy_id, :bauble_id, :pattern, :touched

  def initialize(params)
    @teensy_id = params["teensy_id"].to_s
    @bauble_id = params["bauble_id"].to_s
    @pattern = params["pattern"].to_s
    @control_type = params["control_type"]
    @controllers = params["controllers"]
    @controllers.each do |c|
      c["teensy_id"] = c["teensy_id"].to_s
      c["touchpad"] = c["touchpad"].to_s
    end
    @touched = false
  end

  def set_pattern(pattern, drivers)
    drivers[@teensy_id].send_command(TeensyDriver::CommandSetPattern, "#{@bauble_id},#{pattern}")
  end

  def touch_event(drivers)
    # See if any of our touch drivers have changed
    current_state = @control_type == "and"
    @controllers.each do |c|
      if @control_type == "and" && !drivers[c["teensy_id"]].nil?
        current_state = current_state && drivers[c["teensy_id"]].touch_pads[c["touchpad"]]
      elsif @control_type == "or" && !drivers[c["teensy_id"]].nil?
        current_state = current_state || drivers[c["teensy_id"]].touch_pads[c["touchpad"]]
      end
    end
    if current_state != @touched
      # We've changed state
      @touched = current_state
      if @touched
        drivers[@teensy_id].send_command(TeensyDriver::CommandBaubleTouched, @bauble_id)
      else
        drivers[@teensy_id].send_command(TeensyDriver::CommandBaubleReleased, @bauble_id)
      end
    end
  end
end

