#!/bin/bash

# 에러 발생 시 스크립트 중단
set -e

# 색상 정의
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

log_header() {
    echo -e "\n${BOLD}${CYAN}=========================================${NC}"
    echo -e "${BOLD}${CYAN}  $1 ${NC}"
    echo -e "${BOLD}${CYAN}=========================================${NC}"
}

log_info() {
    echo -e "${BLUE}ℹ️  $1 ${NC}"
}

log_success() {
    echo -e "${GREEN}✅  $1 ${NC}"
}

log_warn() {
    echo -e "${YELLOW}⚠️  $1 ${NC}"
}

error_handler() {
    echo -e "\n${RED}❌  ExternalLib Build Failed! (Line: $1)${NC}"
}
trap 'error_handler $LINENO' ERR

ROOT="$(cd "$(dirname "$0")" && pwd)"
JOBS="${JOBS:-16}" 
BUILD_DIR="$ROOT/Build"

build() {
  log_info "Configuring CMake..."
  cmake -S "$ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release --log-level=WARNING

  log_info "Building with $JOBS jobs..."
  cmake --build "$BUILD_DIR" --parallel "$JOBS"
}

clean() {
  log_info "Cleaning build files..."
  
  if [ -d "$BUILD_DIR" ]; then
      rm -rf "$BUILD_DIR"
      log_info "Removed directory: $BUILD_DIR"
  else
      log_warn "Build directory not found, nothing to clean."
  fi
}

log_header "ExternalLib Build Process Started"

build
log_success "Build Completed Successfully!"

log_header "Cleanup Process Started"
clean
log_success "Temporary Build Files Cleaned!"

echo -e "\n${BOLD}  All Tasks Finished!${NC}"
