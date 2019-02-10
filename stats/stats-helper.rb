require 'csv'
require 'statsample'

data = CSV.read('press-3-0.csv')

backgrounds = data.collect { |e| e[5].to_f }
readings = data.collect { |e| e[4].to_f }
thresholds = data.collect { |e| e[4].to_f - e[5].to_f }

puts "#{data.length} readings"
puts
puts "Stats        min\tmax\tmean\tmedian\tstddev"
b = Daru::Vector.new(backgrounds)
r = Daru::Vector.new(readings)
t = Daru::Vector.new(thresholds)

puts "Backgrounds: #{b.min}\t#{b.max}\t#{b.mean}\t#{b.median}\t#{b.std}"
puts "   Readings: #{r.min}\t#{r.max}\t#{r.mean}\t#{r.median}\t#{r.std}"
puts " Thresholds: #{t.min}\t#{t.max}\t#{t.mean}\t#{t.median}\t#{t.std}"

new_threshold = 450

puts
puts "Recalculating based on threshold of #{new_threshold}"
puts

trimmed = data.reject { |e| e[4].to_f - e[5].to_f < new_threshold }

backgrounds = trimmed.collect { |e| e[5].to_f }
readings = trimmed.collect { |e| e[4].to_f }
thresholds = trimmed.collect { |e| e[4].to_f - e[5].to_f }

puts "#{trimmed.length} readings"
puts
puts "Stats        min\tmax\tmean\tmedian\tstddev"
b = Daru::Vector.new(backgrounds)
r = Daru::Vector.new(readings)
t = Daru::Vector.new(thresholds)

puts "Backgrounds: #{b.min}\t#{b.max}\t#{b.mean}\t#{b.median}\t#{b.std}"
puts "   Readings: #{r.min}\t#{r.max}\t#{r.mean}\t#{r.median}\t#{r.std}"
puts " Thresholds: #{t.min}\t#{t.max}\t#{t.mean}\t#{t.median}\t#{t.std}"

(80..800).each do |threshold|
  data.reject! { |e| e[4].to_f - e[5].to_f < threshold }
  puts "#{threshold},#{data.length}"
end

