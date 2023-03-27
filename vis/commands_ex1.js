window.prog = `
1
2,x=200,y=100,color=yellow
3,x=100,y=200,shape=star
1-2,color=red,label=OK
1-3
draw
p,Adding vertex
pause
4
pause
p,Coloring vertex
4,color=yellow,shape=box,label=asdfg;dfghj;dfghj
pause
p,Adding edges
1-4,label=A
2-4,label=B
3-4,label=C
pause
p,Adding edges
1-4,label+=A
2-4,label+=B
3-4,label+=C;и еще строка;и еще одна
`
