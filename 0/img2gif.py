#
from PIL import Image
#
#
#
numframes = 128
#
prefix    = 'frame'
#
padding   = 3
#
#
#
ani = []
#
for j in range( numframes ) :
    #
    num = f'{j}'
    #
    while len(num) < padding : num = ( '0' + num )
    #
    img = Image . open( f'img/{prefix}{num}.pgm' )
    #
    ani . append( img . copy() )
    #
#
#
#
ani[0] . save( 'movie.gif' ,  save_all       = True      , \
                              append_images  = ani[1:]   , \
                              duration       = 40        , \
                              loop           = 1         )