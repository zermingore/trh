#!/bin/sh

cd db && sqlite3 db.sql '.read default_schema.sql' && mv -i db.sql ../
