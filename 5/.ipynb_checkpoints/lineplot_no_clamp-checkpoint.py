#
import matplotlib . pyplot as plt
#
fnamelist = 'ants bear bird claw eyes hawk lion wolf elvis' . split()
#
# fnamelist = [ 'elvis' ]
#
for fname in fnamelist :
    #
    a = [0] * 255
    #
    txt = open( f'right/{fname}.txt' ) . read() . split()
    #
    for j in range(255) :
        #
        a[j] = float( txt[j] )
        #
    #
    plt . plot( range(1,256) , a )
    #
    plt . xticks( [ 0 , 42 , 85 , 127 , 170 , 212 , 255 ] )
    #
    plt . ylim( 0 , 1 )
    #
    plt . savefig( f'right/lineplot_{fname}.png' )
    #
    plt . clf()
    #
#
# end
#
