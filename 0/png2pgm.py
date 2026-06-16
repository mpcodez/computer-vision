#
from PIL import Image
#
fname = 'elvis'

from sys import argv
#
if len( argv ) > 1 : fname = argv[1]

#
# identify *.png
#
img = Image . open( f'{fname}.png' )
#
# grayscale mode
#
img = img . convert( 'L' )
#
# P5 binary raw
#
img . save( f'{fname}.pgm' )
#
# end
#
