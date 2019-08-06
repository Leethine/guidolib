

# Clef, Key, Meter 

This example shows the use of \clef, \key and \meter tags.

~~~~~~
{
	[ \barFormat<"system"> 
	  \clef<"violin"> \key<"D"> \meter<"4/4"> c f a g f# c#2 a1 b ],
	[ \clef<"alto">   \key<2>   \meter<"C"> c c c c \acc(c#) c# c# c# ],
	[ \clef<"tenor">  \key<-2>  \meter<"2+3+3/8"> c/8 b&0 a gf e& d c d e& f g a b c1 d ],
	[ \clef<"bass">   \key<free="f[0.5]c">  \meter<"C/"> \alter<0.5>(c0/2 f g f)
}
~~~~~~
{!GMN/examples/clefkeymeter.html!}