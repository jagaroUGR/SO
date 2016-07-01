#!/bin/sh

echo "PATH=$PATH:$HOME/Universidad/SO/practicas/modulo1/sesion4"> crontab_reducelista
echo "\n\n" >> crontab_reducelista
echo "*/1 * * * * for i in \`seq 1 20\`; do touch /tmp/varios/core\$i; done" >> crontab_reducelista
echo "*/1 * * * * listaCores.sh" >> crontab_reducelista
echo "*/1 * * * * reducelista.sh" >> crontab_reducelista
