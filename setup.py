from distutils.core import setup, Extension

module = Extension(
    'example_module',
    sources=['example_module.c']
)

setup(
    name = '',
    version = '0.0.1',
    description = '',
    ext_modules = [module],

    url='',
    author='',
    author_email=''
)


#python3 setup.py build
