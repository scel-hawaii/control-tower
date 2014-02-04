# A simple python program to strip and parse our schemas 
import re

# Removes comments from a C file 
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ""
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

# Removes blank lines from a C file
def blankline_remover(text):
	return "".join([s for s in text.splitlines(True) if s.strip("\r\n")])

# Main code
if __name__ == "__main__":
	file = open('sample_struct.c', 'r')
	file_read = file.read()
	print file_read

	test_file = open('test123.c', 'w')

	# Remove Comments 
	awesome = comment_remover(file_read)
	awesome = blankline_remover(awesome);

	print awesome

	test_file.write(awesome)
