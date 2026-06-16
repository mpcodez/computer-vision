#
from PIL import Image
#
#
#
numframes = 100
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
    img = Image . open( f'challenge2/{prefix}{num}.png' )
    #
    ani . append( img . copy() )
    #
#
#
#
ani[0] . save( 'movie.gif' ,  save_all       = True      , \
                              append_images  = ani[1:]   , \
                              duration       = 80        , \
                              loop           = 1         )