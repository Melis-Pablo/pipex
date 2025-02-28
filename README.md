# Pipex

## 📋 Project Overview

Pipex is a program that simulates the functionality of Unix pipes in the shell. This project demonstrates a deep understanding of Unix process management, file descriptors, and inter-process communication.

The program replicates the behavior of the shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

By implementing this mechanism from scratch, I gained practical knowledge of how Unix handles command execution and data flow between processes.

## 🔧 Features

### Core Functionality
- Execute commands in a pipeline similar to Unix shell pipes
- Redirect standard input from a file
- Redirect standard output to a file
- Error handling for all system calls
- Memory management to avoid leaks

### Bonus Features
- Support for multiple commands in the pipeline
- Implementation of "here_doc" functionality (heredoc)
- Handling of append mode for output files

## 🚀 Implementation Details

### Process Architecture

The implementation uses a carefully designed architecture with:
- Fork to create child processes for each command
- Pipe to establish communication between processes
- Dup2 to redirect standard input/output
- Execve to execute the commands
- Wait/Waitpid to synchronize parent and child processes

### Memory Safety

Special attention was paid to:
- Proper allocation and freeing of resources
- Handling of file descriptors to prevent leaks
- Careful error checking for all system calls
- Clean termination in all scenarios

## 💻 Usage

### Compilation

```bash
# Clone the repository
git clone https://github.com/Melis-Pablo/pipex.git
cd pipex

# Compile with mandatory features
make

# Compile with bonus features
make bonus
```

### Basic Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

This is equivalent to the shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

### Examples

```bash
# Count the number of lines in the directory listing
./pipex /dev/null "ls -la" "wc -l" outfile

# Find all occurrences of "Hello" and count them
./pipex infile "grep Hello" "wc -l" outfile

# Convert text to uppercase and replace spaces with newlines
./pipex infile "tr '[:lower:]' '[:upper:]'" "tr ' ' '\n'" outfile
```

### Bonus Usage

#### Multiple Pipes
```bash
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

#### Here Document
```bash
./pipex here_doc DELIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
cmd1 << DELIMITER | cmd2 >> outfile
```

## 🔍 Technical Challenges

### Process Management
- Creating and managing multiple child processes
- Ensuring proper termination and resource cleanup
- Handling errors that can occur during process execution

### Pipe Communication
- Setting up pipes between processes
- Properly redirecting standard input/output
- Preventing deadlocks and race conditions

### Command Execution
- Parsing command strings with arguments
- Finding executable files in PATH
- Handling command execution errors

## 🧠 Key Learnings

This project provided in-depth understanding of:
- Unix process creation and management
- Inter-process communication mechanisms
- File descriptor manipulation
- Command execution in a Unix environment
- Complex error handling strategies
- Memory management in multi-process applications

## 📝 Testing

The implementation was tested against various scenarios:
- Commands with different numbers of arguments
- Commands that fail or don't exist
- Files with different permissions
- Edge cases like empty files or very large outputs
- Error conditions like inaccessible files or invalid permissions

## 📚 References

For detailed project requirements, see the [pipex.md](pipex.md) file.

---

*This project is part of the 42 School Common Core curriculum.*