#!/bin/bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"

SHADER_DIR="$ROOT_DIR/shaders"

CPP_OUT="$1"
HPP_OUT="$2"

mkdir -p "$(dirname "$CPP_OUT")"
mkdir -p "$(dirname "$HPP_OUT")"

cat > "$HPP_OUT" <<EOF
// Auto-generated file. Do not edit.

#pragma once

namespace Wrench::Renderer::EmbeddedShaders {

EOF

cat > "$CPP_OUT" <<EOF
// Auto-generated file. Do not edit.

#include "_embedded_shaders.hpp"

namespace Wrench::Renderer::EmbeddedShaders {

EOF

for shader in "$SHADER_DIR"/*.glsl; do
    [ -e "$shader" ] || continue

    filename=$(basename "$shader")

    varname=$(echo "$filename" | sed 's/[^a-zA-Z0-9]/_/g')
    if [[ "$varname" =~ ^[0-9] ]]; then
        varname="_$varname"
    fi

    echo "extern const char* const $varname;" >> "$HPP_OUT"

    cat >> "$CPP_OUT" << EOF
const char* const $varname = R"SHADER(

$(cat "$shader")

)SHADER";

EOF
done

cat >> "$HPP_OUT" <<EOF

}
EOF

cat >> "$CPP_OUT" <<EOF

}
EOF
