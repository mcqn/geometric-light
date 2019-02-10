# TeensyDriver class
# (c) Copyright 2017 MCQN Ltd

class TeensyDriver
  # We're always host 0
  HostId = 0
  CommandIdRequest = 0
  CommandIdResponse = 1
  CommandTouchDown = 2
  CommandTouchRelease = 3
  CommandSetPattern = 4
  CommandBaubleTouched = 5
  CommandBaubleReleased = 6
  CommandStreamTouchReadings = 7
  CommandWitholdTouchReadings = 8
  CommandSetTouchThreshold = 9

  attr_accessor :id, :touch_pads

  def initialize(port, logfile =nil)
    @port = port
    @logfile = logfile
    @id = -1
    @sp = SerialPort.new(port, 115200)
    @sp.read_timeout = 5
    @touch_pads = { "0" => false, "1" => false }
    # Ask the Teensy at the other end what its ID is
    send_command(CommandIdRequest)
    sleep 0.5 # Give it a moment to reply
    process_data
  end

  def update_settings(params)
    params["touchpads"].each do |t|
      send_command(CommandSetTouchThreshold, "#{t['id']},#{t['touch_threshold']}")
    end
  end

  def send_command(aCmd, aData = nil)
    packet = "#{HostId},#{aCmd}"
    unless aData.nil?
      packet = packet + ",#{aData}"
    end
    @logfile.puts packet+", #{Time.now}" unless @logfile.nil?
    @sp.puts packet
  end

  def process_data
    data = @sp.gets
    unless data.nil?
      # We've got a command
      @logfile.puts data.strip+", #{Time.now}" unless @logfile.nil?
      # Strip off the trailing CRLF and parse it
      cmd = data.strip.split(",")
      # First param is our ID
      @id = cmd[0]
      # Now process the command
      if cmd[1] == CommandIdResponse.to_s
        # Nothing to do, we'll already have updated the ID for this Teensy
        #puts "Got ID response"
      elsif cmd[1] == CommandTouchDown.to_s
        @touch_pads[cmd[2]] = true
      elsif cmd[1] == CommandTouchRelease.to_s
        @touch_pads[cmd[2]] = false
      end
    end
  end
end

