DNAViewer
=========

> Experimental application for viewing DNA in interesting ways.

How it Works
============

DNA is composed of four molecules. `{T, C, G, A}` we wont get into the names but at least the initial concept works as follows. 

    start drawing a line-strip made up of points
    
    for each `molecule` in DNA-sequence:
    
      if the `molecule` is 'T'
        move X to the right one
      if the `molecule` is 'T'
        move X to the left one
      if the `molecule` is 'G'
        move Y to down one
      if the `molecule` is 'A'
        move Y to up one
      
      draw the current point / line
      
The key to this project going forward is to come up with much more intuitive ways of visualizing the data. This will involve reasearching DNA and talking to people familiar with the problem space.

[Common DNA Sequences](http://www.algosome.com/resources/common-sequences.html)

Other future improvements include 3-dimensionality to the concept.

Experimental Data Set
=================

- http://corpus.canterbury.ac.nz/descriptions/large/E.coli.html
- http://corpus.canterbury.ac.nz/descriptions/#large

Screenshots
===========

> The first screenshot to be generated from the very first sequence of ECOLI. What's fascinating about this is the near complete cirle that is formed -- there is an infinte number of ways to NOT create something semi-circular; I'm very curious to see what the beginning of other DNA sequences yeild. 

![ScreenshotOne](https://raw.github.com/PJensen/DNAViewer/master/screenshots/02232013ECOLI.png)
