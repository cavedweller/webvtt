#!/bin/sh
# Configuration
start_dir=$(dirname $0)
# Modify start-dir because script is not in root directory
start_dir="${start_dir}/../.."

project_name="webvtt"
project_description="Parser library implementing the WebVTT caption and subtitle format"
copyright_holders="Mozilla Foundation and Contributors"
copyright_year="2013"
license_type=
license_file="scripts/license/template.erb"
wrap_lines="70"
syntax_file="scripts/license/syntax.yml"
reverse=
dry=

# Actions you'd like to perform:
actions() {
  MAINFILES="*.am *.ac *.sh src include" 
  TEXTFILES="LICENSE"
  xlicense "${MAINFILES}"
  syntax_file="scripts/license/syntax.text.yml"
  xlicense "${TEXTFILES}"
}

####################################################################
#
# Program code below:
#
#####################################################################

paths() {
  if [ -n "$1" ]; then
    _paths=$(echo $1 | sed -re 's/([^\]{0,0})[ \n]{1,}/\1:/gp')
    echo "${_paths}"
  fi
}

main() {
  files=
  # Check if copyright-header gem is present on system and usable:
  platform=$(uname -o)
  if [ $? -eq 0 -a "x$(echo ${platform} | \
    sed -n 's/(Msys)|(MINGW32.*)|(Cygwin)$/windows/gp')" = "xwindows" ]; then
    windows="yes"
  fi

  copyright-header 2>&1 >/dev/null
  if [ $? -ne 1 ]; then
    echo "copyright-header gem does not seem to be installed.\n"
    echo "Install globally with \`sudo gem install copyright-header\`\n"
    echo "If ruby or rubygems are not installed, they must be"
    echo "installed first:"
    echo "    ruby: http://www.ruby-lang.org"
    echo "rubygems: http://rubygems.org"
    exit 1
  fi

  for arg in "$@"
  do
    if [ "x${arg}" = "x-r" ]; then
      reverse="yes"
    elif [ "x${arg}" = "x-n" ]; then
      dry="-n"
    else
    # Assuming it's a path
      if [ -z "${files}" ]; then
        files="${arg}"
      else
        files="${files} ${arg}"
      fi
    fi
  done

  if [ -n "${files}" ]; then
    xlicense "${files}"
  else
    actions
  fi
}

_license() {
  syntax=
  lictyp=
  licopt=
  wrap=80
  if [ -n "${license_type}" ]; then
    lictyp="--license"
    licopt="${license_type}"
  elif [ -n "${license_file}" ]; then
    lictyp="--license-file"
    licopt="${start_dir}/${license_file}"
  fi
  if [ -n "${syntax_file}" ]; then
    syntax="--syntax=${start_dir}/${syntax_file}"
  fi
  if [ -n "${wrap_lines}" ]; then
    wrap="${wrap_lines}"
  fi
  if [ -z "$1" -o -z "$2" ]; then
    echo "Error"
    return 1
  fi
  copyright-header ${dry} --copyright-software="${project_name}" \
  --copyright-software-description="${project_description}" \
  --copyright-holder="${copyright_holders}" \
  --copyright-year="${copyright_year}" \
  --output-dir="${start_dir}" --word-wrap="${wrap}" \
  ${lictyp}="${licopt}" \
  $1="$2" ${syntax} ${path} ${lic}
}

license() {
  _=
  if [ -n "$1" ]; then
    _license "--add-path" "$(paths "$1")"
  fi
}

unlicense() {
  if [ -n "$1" ]; then
    _license "--remove-path" "$(paths "$1")"
  fi
}

xlicense() {
  arg="--add-path"
  if [ "x${reverse}" = "xyes" ]; then
    arg="--remove-path"
  fi
  _license ${arg} "$(paths "$1")"
}

main "$@"
