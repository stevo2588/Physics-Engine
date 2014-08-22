import os
import SCons

#------------------------- Variables ---------------------------------------------
MINGW32_dir = 'D:\\Development\\Tools\\Programs\\Other\\MinGW'
GPP_COMPILER_path = MINGW32_dir + '\\bin\\mingw32-g++'

SFML_dir = 'D:\\Development\\Tools\\SDKs_APIs_Libraries\\SFML\\SFML-2.0_1-17-13'   # SFML directory
QT_dir = 'D:\\Development\\Tools\\SDKs_APIs_Libraries\\qt\\qt-4.8-build_1-28-13'   # Qt directory
#GLEW_dir = 'D:\\Development\\Tools\\SDKs_APIs_Libraries\\Other\\GLEW\\glew-1.10.0' # GLEW directory

# include paths
inc_paths = ['.\\include',
             '.\\include\\GUI',
             SFML_dir+'\\include']
	
# library paths	
lib_paths = [SFML_dir+'\\lib']

#libraries
libs = ['libsfml-main.a',
		'libsfml-system.a',
		'libsfml-graphics.a',
		'libsfml-window.a',
		'opengl32']

#------------- Create a base construction environment ------------------------
baseEnv = Environment(  ENV = os.environ,
                        CPPPATH = inc_paths,
                        LIBPATH = lib_paths,
                        LIBS = libs,
                        CCFLAGS=['-std=c++11', '-DGLEW_STATIC', '-O0', '-ggdb3'],
                        tools = ['mingw'],
                        CC = GPP_COMPILER_path )


#------------------- Create Qt environment from base --------------------------
qtEnv = baseEnv.Clone()
#baseEnv.AppendENVPath('CPPPATH', QT_dir + '\\include' )
#baseEnv.AppendENVPath('LIB', QT_dir + '\\lib') # add to existing LIB
# Set QT4DIR and PKG_CONFIG_PATH
qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(QT_dir, 'lib/pkgconfig')
qtEnv['QT4DIR'] = QT_dir

qtEnv.Tool('qt4') # Add qt4 tool
#...further customization of qt env

#--------------------------- Export environments --------------------------------
Export('baseEnv qtEnv')

#----------------------------- SConscripts --------------------------------------
SConscript( 'SConscript', variant_dir='bin\\Release', duplicate=0, exports={'MODE':'release'} )
#SConscript( 'SConscript', variant_dir='bin\\Debug', duplicate=0, exports={'MODE':'debug'} )

