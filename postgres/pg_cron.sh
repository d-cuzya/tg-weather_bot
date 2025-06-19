#!/bin/bash

echo "0 0 * * * psql -U botuser -d botdb -f /docker-entrypoint-initdb.d/reset_count.sql" > /etc/cron.d/reset_cron
chmod 0644 /etc/cron.d/reset_cron
crontab /etc/cron.d/reset_cron
