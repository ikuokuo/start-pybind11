MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))

.DEFAULT_GOAL := build

SHELL := /bin/bash

# Variables

ECHO ?= echo -e
FIND ?= find

BUILD_DIR ?= _build
OUTPUT_DIR ?= _output
INSTALL_DIR ?= $(MKFILE_DIR)/_install
DEPLOY_DIR ?= _deploy

MAKE ?= make
MAKE_OPTIONS ?= -j$$(nproc)

CMAKE ?= cmake
CMAKE_OPTIONS ?= \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_INSTALL_PREFIX=$(INSTALL_DIR)
# make CMAKE_OPTIONS="-DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install"

# Functions

define echo
	text="$1"; options="$2"; \
	[ -z "$$options" ] && options="1;33"; \
	$(ECHO) "\033[$${options}m$${text}\033[0m"
endef

define md
	([ -e "$1" ] || (mkdir -p "$1" && $(call echo,MD: $1,33)))
endef

define rm
	[ ! -h "$1" ] && [ ! -e "$1" ] || (rm -r "$1" && $(call echo,RM: $1,33))
endef

define rm_f
	dir="$2"; [ -e "$${dir}" ] || dir="."; \
	$(FIND) "$${dir}" -mindepth 1 -maxdepth 1 -name "$1" | while read -r p; do \
		$(call rm,$$p); \
	done
endef

# Goals

.PHONY: build
build:
	@$(call md,$(BUILD_DIR))
	cd $(BUILD_DIR); \
	$(CMAKE) $(CMAKE_OPTIONS) ..; \
	$(MAKE) $(MAKE_OPTIONS)

.PHONY: install
install: build
	@cd $(BUILD_DIR); $(MAKE) install

.PHONY: cleanlog
cleanlog:
	@$(call rm_f,*INFO*)
	@$(call rm_f,*WARNING*)
	@$(call rm_f,*ERROR*)
	@$(call rm_f,*FATAL*)
	@$(call rm,log)

.PHONY: clean
clean: cleanlog
	@$(call rm,$(BUILD_DIR))
	@$(call rm,$(OUTPUT_DIR))
	@$(call rm,$(INSTALL_DIR))
	@$(call rm,$(DEPLOY_DIR))

.PHONY: print
print:
	@$(call echo,Make $@)
	@echo MKFILE_PATH: $(MKFILE_PATH)
	@echo MKFILE_DIR: $(MKFILE_DIR)
	@echo SHELL: $(SHELL)
	@echo ECHO: $(ECHO)
	@echo MAKE: $(MAKE)
	@echo MAKE_OPTIONS: $(MAKE_OPTIONS)
	@echo CMAKE: $(CMAKE)
	@echo CMAKE_OPTIONS: $(CMAKE_OPTIONS)
