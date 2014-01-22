import urllib
import shutil
from zipfile import ZipFile

urllib.urlretrieve("http://www.sfml-dev.org/download/sfml/2.1/SFML-2.1-windows-vc11-32bits.zip", "SFML-2.1-windows-vc11-32bits.zip")
urllib.urlretrieve("https://bitbucket.org/maxisoft/racing/downloads/Box2D.zip", "Box2D.zip")
urllib.urlretrieve("https://bitbucket.org/maxisoft/racing/downloads/Yaml-cpp.zip", "Yaml-cpp.zip")
urllib.urlretrieve("https://dl.dropboxusercontent.com/s/3yt31wj9vsnzzes/Boost.zip?dl=1", "Boost.zip")

with ZipFile('SFML-2.1-windows-vc11-32bits.zip') as myzip:
	myzip.extractall()

with ZipFile('Box2D.zip') as myzip:
	myzip.extractall()

with ZipFile('Yaml-cpp.zip') as myzip:
	myzip.extractall()

with ZipFile('Boost.zip') as myzip:
	myzip.extractall()

shutil.move('./SFML-2.1', './VS-2012-SFML-2.1')
