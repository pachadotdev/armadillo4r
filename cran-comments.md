## R CMD check results

0 errors | 0 warnings | 0 note

Dear Prof Dr Uwe Ligges:

I hope you are doing well.

armadillo4r is not really a rename cpp11armadillo, it uses cpp4r,
which is a rewrite of cpp11 motivated by a practical problem:
using complex numbers to run some Macroeconometrics models that
are not so painful to write with Armadillo, but where the complex
part of some matrices is really important when it comes to
evaluate a system's controllability.

While cpp4r armadillo is based on cpp11, it is a bit like what
'CyanogenMod' is to Stock Android, there is a common foundation but
then it goes into a different direction.

As Prof Dr Balamuta from UCB pointed out: "... I do appreciate two
aspects of this work. First, the features you've added are indeed
useful. Complex number support, Roxygen integration, and the
flexibility improvements all address real pain points. Second, I like
that you're moving toward more permissive licensing (MIT instead of
GPL). This makes it easier for folks working in corporate environments
to feel comfortable adopting the tooling without legal concerns."

While armadillo4r, which is a "departure" from cpp11armadillo (both
will be maintained), was created to make my own model fitting simpler
but then the "unexpected" uses came up. So far, users from different
universities have emailed me besides my own Macro seminar fellows
about how to install it in different environments similar to
Cirrus/Eureka2/Niagara, which are restricted HPC services where the
vendoring feature makes life simpler for researchers and the IT teams
that often assist with setups.

My apologies for the very long email but I must also send a big THANK
YOU to all CRAN developers/maintainers/donors. Writing a PhD thesis
can be hard for the wrong reasons (i.e., no Stata/MATLAB license) and
using R has really made things easier on my end. Many users don't
realise how important it is to have access to transparent statistical
routines and the possibility to expand those. I will soon be sending
new versions of kendallknight and capybara (which now depends on
armadillo4r) to reflect the complex numbers considerations and some
minor speed ups on cpp4r vs cpp11 side.

Be safe and well,
MVS
