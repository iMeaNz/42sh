<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h1 align="center">42sh</h1>
  <h3 align="center">A homemade shell</h3>

</div>

<!-- TABLE OF CONTENTS -->
<details>
    <summary>Table of Contents</summary>
    <ol>
        <li>
            <a href="#about-the-project">About The Project</a>
            <ul>
                <li><a href="#Mandatory section">Mandatory section</a></li>
                <li><a href="#Optional section">Optional section</a></li>
            </ul>
        </li>
        <li>
            <a href="#getting-started">Getting Started</a>
            <ul>
                <li><a href="#installation">Installation</a></li>
            </ul>
        </li>
    </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This project is one of the tree first-year Epitech's final project. The goal is to recreate a Unix Shell.  
This projects consists of two sections :
- a mandatory section, which must be completed (see below).
- an optional section, which is only evaluated if the mandatory section is fully functionnal.    
The reference shell for this project is TCSH.

### Mandatory section
- Spaces and tabulations ✅
- $PATH and environnement handling ✅
- Errors and return value ✅
- Redirections ('<', '<<', '>' '<<') ✅
- Pipes ('|')
- Builtins functions : cd, echo, exit, setenv and unsetenv ✅
- Separators (';', '&&', '||') ✅

### Optional section
- Inhibitors ('\') ✅
- Globbings ('*', '?', '[]' '{}') ✅
- Job control ('&', fg) ✅
- Backticks ('``') ✅
- Parentheses ❌
- Variables (local and env) ✅
- Special variables (term, precmd, cwdcmd, ignoreof...) ❌
- History ('!') ✅
- Aliases ✅
- Line edition (multiline, dynamic rebinding, auto-completion dynamic) ❌
- Scripting ❌

## Getting started
1. Clone the repository
  ```sh
  git clone git@github.com:iMeaNz/42sh.git
  ```
2. Compile the program
  ```sh
  make
  ```
3. Run the program
  ```sh
  ./42sh
  ```