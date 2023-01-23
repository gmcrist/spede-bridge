#!/usr/bin/env bash

spede_root=${SPEDE_ROOT:-/opt/spede}

declare -A install_dirs
install_dirs=(
    [bin]="bin/linkdli"
    [lib]="lib/gdb0.o lib/ctors.o lib/i386-stub.o lib/support.o lib/finish.o lib/libi386.a"
    [include]="include/spede"
)

function main() {
    echo "Creating SPEDE Root directory '${spede_root}'"
    install -d ${spede_root} || return $?

    for dir in ${!install_dirs[*]}; do
        dest=${spede_root}/${dir}

        echo "Creating directory '${dir}'..."
        install -d ${dest} || return $?
        echo ${dest}

        for file in ${install_dirs[${dir}]}; do
            if [ -d ${file} ]; then
                echo "Copying directory '${file}' to '${dest}'"

                find ${file} -type d -exec echo "{}" \; -exec install -d "{}" ${spede_root}/"{}" \;
                find ${file} -type f -exec echo "{}" \; -exec install "{}" ${spede_root}/"{}" \;

#                (cd ${file} && find . -type d -exec echo "{}" \; -exec install -d "{}" ${dest}/"{}" \;)
#                (cd ${file} && find . -type f -exec echo "{}" \; -exec install "{}" ${dest}/"{}" \;)
            else
                echo "Copying '${file}' to '${dest}'..."
                install ${file} ${dest} || return $?
            fi
        done
    done

    echo "Installation complete"
}

main $@
exit $?
