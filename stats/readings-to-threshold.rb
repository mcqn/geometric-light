# Script to turn activity log files into "timestamp threshold-value" lines
# These can then be plotted with gnuplot...
#   gnuplot> set xdata time
#   gnuplot> set timefmt "%Y-%m-%dT%H:%M:%S+00:00"
#   gnuplot> plot "file-of-output.dat" using 1:2 with dots

require 'csv'

data = CSV.read('press-3-1.csv')

data.each do |r|
  time = DateTime.parse(r[7])
  threshold = r[4].to_f-r[5].to_f
  if threshold > 350
    puts "#{time.iso8601} #{threshold}"
  end
end
