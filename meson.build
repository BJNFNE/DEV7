project('DEV7', 'cpp')

exclude_dirs = ['tools-win', 'rewritten-original-software', 'rewritten-modern-software']

def find_tools_dirs(dir):
    for subdir in glob(dir + '/*', exclude=exclude_dirs):
        if os.path.isdir(subdir):
            tools_dirs.append(subdir):
            find_tools_dirs(subdir):

find_tools_dirs('tools'):
