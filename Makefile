#
# JacobiParallel
#
# Patrik Rosini
#

#App name
APPNAME = jacobip

#Compiler
CXX		= icc -std=c++11
INCLUDES	= -I /home/spm1501/fastflow
CXXFLAGS  	= -Wall
OPTFLAGS	= -O3 -pthread

#Rules
.PHONY: all

all: clean jacobip_ORIG jacobip_VRED

phi: OPTFLAGS += -mmic -DNO_DEFAULT_MAPPING
phi: jacobip_ORIG jacobip_VRED

#Make Rules

jacobip_ORIG: clean-jacobip_ORIG main.cpp algos.cpp utils.cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INCLUDES) -DORIG main.cpp algos.cpp utils.cpp -o $(APPNAME)_ORIG
	@echo "$(APPNAME)_xeon compiled..."
jacobip_VRED: clean-jacobip_VRED main.cpp algos.cpp utils.cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INCLUDES) -DVRED main.cpp algos.cpp utils.cpp -o $(APPNAME)_VRED
	@echo "$(APPNAME)_VRED compiled..."

.PHONY: clean
clean: jacobip_ORIG

.PHONY: clean-jacobip_ORIG
clean-jacobip_ORIG:
	rm -f $(APPNAME)_ORIG
	@echo "$(APPNAME)_ORIG cleaned..."

.PHONY: clean-jacobip_VRED
clean-jacobip_VRED:
	rm -f $(APPNAME)_VRED
	@echo "$(APPNAME)_VRED cleaned..."