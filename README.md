**Pipex project school 42**

<p align="center">
  <img width="820" height="180" src="https://www.google.com/url?sa=i&url=http%3A%2F%2Ftvaira.free.fr%2Fos%2Ftp-sys-tubes.pdf&psig=AOvVaw1z36Q4Oz0lzBEDtKE43_y0&ust=1635166941554000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCKD3uN6N4_MCFQAAAAAdAAAAABAD">
</p>

Your objective is to code the Pipex program.
It should be executed in this way:
$> ./pipex file1 cmd1 cmd2 file2
Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with
their parameters.
The execution of the pipex program should do the same as the next shell command:
$> < file1 cmd1 | cmd2 > file2
III.1 Examples
$> ./pipex infile ``ls -l'' ``wc -l'' outfile
should be the same as “< infile ls -l | wc -l > outfile”
$> ./pipex infile ``grep a1'' ``wc -w'' outfile
should be the same as “< infile grep a1 | wc -w > outfile”

Bonus part
Bonuses will be evaluated only if your mandatory part is PERFECT.
By PERFECT we naturally mean that it needs to be complete, that it
cannot fail, even in cases of nasty mistakes like wrong uses, etc.
It means that if your mandatory part does not obtain ALL the points
during the grading, your bonuses will be entirely IGNORED.
• Handle multiple pipes :
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Must be equivalent to :
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
• Support « and » when the first parameter is "here_doc"
$> ./pipex here_doc LIMITER cmd cmd1 file
Must be equivalent to:
cmd << LIMITER | cmd1 >> file
