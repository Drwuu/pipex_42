**Pipex project school 42**

<h1 align="center">
  Pipex project school 42
</h1>
<p align="center">
  <img src="https://www.tutorialspoint.com/inter_process_communication/images/pipe_with_two.jpg">
</p>

<p align="center">
Your objective is to code the Pipex program.
It should be executed in this way:
$> ./pipex file1 cmd1 cmd2 file2
Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with
their parameters.
The execution of the pipex program should do the same as the next shell command:
$> < file1 cmd1 | cmd2 > file2
</p>
<p align="center">
III.1 Examples
$> ./pipex infile ``ls -l'' ``wc -l'' outfile
should be the same as “< infile ls -l | wc -l > outfile”
$> ./pipex infile ``grep a1'' ``wc -w'' outfile
should be the same as “< infile grep a1 | wc -w > outfile”
</p>
  
<h1 align="center">
Bonus part
</h1>
<p align="center">
Bonuses will be evaluated only if your mandatory part is PERFECT.
By PERFECT we naturally mean that it needs to be complete, that it
cannot fail, even in cases of nasty mistakes like wrong uses, etc.
It means that if your mandatory part does not obtain ALL the points
during the grading, your bonuses will be entirely IGNORED.
</p>
<p align="center">
• Handle multiple pipes :
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Must be equivalent to :
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
• Support « and » when the first parameter is "here_doc"
$> ./pipex here_doc LIMITER cmd cmd1 file
Must be equivalent to:
cmd << LIMITER | cmd1 >> file
</p>
