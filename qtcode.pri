PROJECT_DIR = $$PWD
CONFIG(debug,debug|release){
    DIST_DIR = $$PROJECT_DIR/bin/debug
}else{
    DIST_DIR = $$PROJECT_DIR/bin/release
}

BIN_DIST_DIR = $$DIST_DIR
DEPENCE_DIR = $$PROJECT_DIR/dependence

PLUGIN_PATH = $$BIN_DIST_DIR/plugins
