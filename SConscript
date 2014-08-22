#SConscript('SConscript', build_dir='.build_release', duplicate=0, exports={'MODE':'release'})
#SConscript('SConscript', build_dir='.build_debug', duplicate=0, exports={'MODE':'debug'})

# Get the Qt4 environment
Import('qtEnv')
env = qtEnv.Clone() # Clone it

# Patch it
env.EnableQt4Modules(['QtGui', 'QtCore']) # Enable modules
env['QT4_DEBUG'] = 1

# Create ui headers
env.Uic4(Glob('assets\\UI\\*.ui'))

# Use it
sources = Glob('src\\*.cpp') + Glob('src\\GUI\\*.cpp') + Glob('src\\*.c')
# Use the "Program" builder method to create a program, or executable, from specified source files
# (Other builder methods are "Object", to create .o files, "Library", to create libraries, "Java", to create .class files, etc.)
env.Program(target='PhysicallyBased',
            source=sources)

				
