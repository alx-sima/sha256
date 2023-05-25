#!/usr/bin/ruby
# Copyright (C) 2023 Alexandru Sima (312CA) #
#
# Script de test pentru executabil.
#
# Testeaza daca output-ul executabilului este identic cu cel al executabilului 
# original pentru fisiere cu continut generat aleator.
#
# Argumente:
#   - my_exec: calea catre executabilul de testat
#   - orig_exec: calea catre executabilul original
#   - number_of_files: numarul de fisiere de testat (optional, default 2)

if ARGV.length < 2
  puts "Usage: #{$0} <my_exec> <original_exec> [number_of_files]"
  exit 1
end

my_exec = ARGV[0]
orig_exec = ARGV[1]

nr_files = if ARGV.length < 3 then 2 else ARGV[2].to_i end
    
files = (1..nr_files).map { |file|
  block_size = rand(1024)
  block_count = rand(100)

  file = `mktemp`.strip
  system "dd if=/dev/random of=#{file} bs=#{block_size}K count=#{block_count}"

  file
}.join " "

output = `#{my_exec} #{files}`
expected = `#{orig_exec} #{files}`

if output != expected
  puts "Test failed!"
  puts "Output: #{output}"
  puts "Expected: #{expected}"
  exit 1
end

puts "Test passed!"