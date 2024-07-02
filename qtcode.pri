PROJECT_DIR = $$PWD
CONFIG(debug,debug|release){
    DIST_DIR = $$PROJECT_DIR/bin/debug
}else{
    DIST_DIR = $$PROJECT_DIR/bin/release
}

BIN_DIST_DIR = $$DIST_DIR #生成路径
PLUGIN_PATH = $$BIN_DIST_DIR/plugins #生成插件路径
INS_HEAD_DIR = $$BIN_DIST_DIR/include #头文件安装路径
INS_LIB_DIR = $$BIN_DIST_DIR/lib #lib库安装路径

SRC_DIR = $$PROJECT_DIR/src # 代码路径
DEPENCE_DIR = $$PROJECT_DIR/dependence #三方库路径


