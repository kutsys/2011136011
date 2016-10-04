# ~/.bashrc: executed by bash(1) for non-login shells.
#비로그인 쉘들을 위해서 bash(1)을 실행한다
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# /usr/share/doc/bash/examples/startup-files 를 보라 (bash-doc 안에있는)
# for examples

# If not running interactively, don't do anything
# 상호적으로 동작하지 않는다면 아무것도 하지말라
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
# 히스토리 안에 중복된 line이나 공백으로 시작하는 line을 넣지마라
# 더많은 옵션을 위해서는 bash(1)을 참고하라
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
# 덮어쓰지 말고 히스토리 파일에 추가하라
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
# 히스토리의 길이를 셋팅하기 위해서는 bash(1)에 있는 HITSIZE와 HISTFILESIZE를 보라
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
# 매 명령어 이후에 윈도우 사이즈를 체크하고 필요하다면 행과 열의 값을 업데이트하라
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
# 만약 셋팅되어 있다면 경로이름 추가에 사용된 ** 패턴은 모든파일 이나
# 0개 또는 그이상의 디렉토리 그리고 서브디렉토리에 매치가 된다

#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
# less가 택스트가 아닌 입력파일에 더 친근하게 하려면 lesspipe(1)를 보라
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
# 작업하고있는 chroot를 식별할수 있는 변수를 셋팅한다(프롬프트에서 사용된다)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
# 프롬프트를 팬시하게 셋팅한다(색을 원하지 않는다면 non-color로 셋팅)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
# 터미널이 그럴 가능성이 있다면, 색이바뀐 프롬프트에 대해서 언급하지 않는다;
# 유저를 혼란스럽게 하지 않기 위해서 디폴트로서 꺼져있는다: 터미널창의 초점은
# 프롬프트가 아니라 명령어의 결과물에 가있어야 한다

#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	# 우리는 색을 지원한다; Ecma-48(ISO/IEC-6429)와 호환된다는 가정하에
	# 지원이 부족한 경우는 극히 드물고, 그런 경우는 setaf보다는 setf를 
	# 지원해주는 경향이 있다
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
# 이것이 xterm이라면 타이틀을 user$host:dir로 셋팅한다
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
# ls의 색상 지원을 가느앟게 하고 또한 유용한 별칭을 추가한다
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and error
# 색이 입혀진 GCC의 워닝과 에러
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
# 좀더 많은 ls의 별칭
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
# 오래동안 실행되는 명령어에 대해서 "alert"라는 가칭을 추가한다, sleep 10; alert와 같이
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# 별칭의 정의

# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# 너의 추가사항을 직접 넣는 대신에 ~/.bash_aliases와 같은 분리된 파일에 추가할 수 있다

# See /usr/share/doc/bash-doc/examples in the bash-doc package.
# bash-doc package속의 /usr/share/doc/bash-doc/examples를 보자 
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
# 프로그램가능한 완료 기능을들 가능하게 한다(만약 /etc/bash.bashrc나 
# etc/profile sources /etc/bash.bashrc 속에 이미 가능케 되있다면 
# 이것을 굳이 가능하게 할 필요는 없다

if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
