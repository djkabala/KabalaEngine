#!/bin/sh

KABALA_ENGINE_BUNDLE="`echo "$0" | sed -e 's/\/Contents\/MacOS\/KabalaEngine//'`"
KABALA_ENGINE_RESOURCES="$KABALA_ENGINE_BUNDLE/Contents/Resources"

exec "$KABALA_ENGINE_RESOURCES/bin/KabalaEngine"

