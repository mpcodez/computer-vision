#
import matplotlib . pyplot as plt
#
fnamelist = 'ants bear bird claw eyes hawk lion wolf elvis' . split()
#
for fname in fnamelist :
    #
    a = [0] * 256
    #
    txt = open( f'left/{fname}.txt' ) . read() . split()
    #
    for j in range(256) :
        #
        a[j] = int(txt[j])
        #
    #
    plt . plot( a )
    #
    plt . xticks( [ 0 , 42 , 85 , 127 , 170 , 212 , 255 ] )
    #
    plt . ylim( 0 , 4_000 )
    #
    plt . savefig( f'left/histogram_{fname}.png' )
    #
    plt . clf()
    #
#
# end
#
