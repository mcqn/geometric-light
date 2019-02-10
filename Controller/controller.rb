#!/usr/bin/ruby
# controller.rb
# (c) Copyright 2017 MCQN Ltd

require 'serialport'
require 'yaml'
require 'pp'
require './bauble'
require './teensy-driver'

# Read in config
settings = YAML.load_file("settings.yaml")

# Whether or not the lights are on
displaying = true

# Set up the baubles
baubles = []
settings["baubles"].each do |b|
  baubles.push(Bauble.new(b))
end

logfile = nil
unless settings["logfile"].nil?
  logfile = File.open(settings["logfile"], 'a')
  logfile.puts "Started "+Time.now.to_s
end

# Set up the teensys
TeensyCount = settings["teensy_count"]
teensy_drivers = Hash.new

(1..TeensyCount).each do |t|
  td = TeensyDriver.new("/dev/ttyACM#{t-1}", logfile)
  teensy_drivers[td.id] = td
end

# Now we've got the Teensies set up, we can set their threshold parameters
# (We don't wrap that into the previous step as we can't guarantee their
# port mappings)
settings["teensies"].each do |t|
  teensy_drivers[t["teensy_id"].to_s].update_settings(t)
end

while (1)
  # Check what time it is, in case we need to turn things off
  if Time.now.hour >= settings["off_period"]["start"] && Time.now.hour < settings["off_period"]["end"]
    if displaying
      # Turn each bauble off
      baubles.each do |b|
        b.set_pattern(Bauble::PatternOff, teensy_drivers)
      end
      displaying = false
    end
  elsif !displaying
    # We should be on, but we're not
    # Set each bauble to its default pattern
    baubles.each do |b|
      b.set_pattern(b.pattern, teensy_drivers)
    end
    displaying = true
  end
  
  teensy_drivers.each do |id,t|
    t.process_data
  end
  # Deal with any touch events
  # This will basically put us in a busy loop re-checking
  # baubles unnecessarily, but should be okay...
  baubles.each do |b|
    b.touch_event(teensy_drivers)
  end
  sleep 0.01
end
