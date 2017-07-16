#!/usr/bin/env python2.7

import subprocess
import sys

commands = [
		"strace -c -S calls ./search /etc > /dev/null",
		"strace -c -S calls find /etc > /dev/null",
		"strace -c -S calls ./search /etc -exec echo \\{\\} \\; > /dev/null",
		"strace -c -S calls find /etc -exec echo \\{\\} \\; > /dev/null"]

for command in commands:
	print command
	pipe = subprocess.Popen(command, shell=True, stderr=subprocess.PIPE)
	(out, err) = pipe.communicate()
	#print err
	lines = err.splitlines();
	lines = filter(lambda x: 'find' not in x, lines)
	lines = lines[2:-2]
	for line in lines:
		print "{}\t{}".format(line.split()[3], line.split()[-1])
	print

