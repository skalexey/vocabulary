import requests
import json
import sys
import os

this_dir=os.path.dirname( os.path.realpath( __file__ ) )
sys.path.insert( 1, os.path.expanduser('~') + "/Scripts/automation/gcloud" );

from gcloud import *

def get_api_key():
    with open(this_dir + "/api_key", 'r') as file:
        return file.read().rstrip()

api_key = get_api_key()


translate_word( "Hello World" );