#!/usr/bin/env python

import os
from pathlib import Path
import shutil


class Sandbox(object):
    def __init__(self, directory_name):
        self.directory = Path(directory_name)
        if self.directory.exists():
            raise Exception('{} is already exists.'.format(self.directory))
        self.directory.mkdir(parents=True)

    def get_path(self, relpath):
        return self.directory / relpath

    def command(self, com):
        return os.system('cd {} && {}'.format(self.directory, com))

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        assert self.directory.exists() and self.directory.is_dir()
        shutil.rmtree(self.directory)
        return False
