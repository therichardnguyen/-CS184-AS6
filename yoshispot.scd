(Material pinkmat
    (color .9 .5 .5)
    (ka .1) (kd .7) (ks .5) (ksp 20) (ksm 0) (kt 0) (ktn 1)
)

(Material groundmat
    (color .4 .7 .2)
    (ka .1) (kd .6) (ks .3) (ksp 1) (ksm 1) (kt 0) (ktn 1)
)

(Material skymat
    (color .2 .5 1)
    (ka .1) (kd .8) (ks .1) (ksp .5) (ksm 1) (kt 0) (ktn 1)
)

(Material skinmat
    (color .4 .7 .2)
    (ka .1) (kd .6) (ks .3) (ksp 1) (ksm 1) (kt 0) (ktn 1)
)
(Material eyemat
    (color 1 1 1)
    (ka 0.5) (kd .8) (ks .1) (ksp .5) (ksm 1) (kt 0) (ktn 1)
)

(Material pupilmat
    (color 0 0 0)
    (ka 0) (kd 0) (ks 0) (ksp 1) (ksm 1) (kt 0) (ktn 1)
)
(Material scalemat
    (color 0.95 0.55 0.16)
    (ka 0.5) (kd .8) (ks .1) (ksp .5) (ksm 1) (kt 0) (ktn 1)
)

(Sphere usph (radius 1.0) (material groundmat))
(Sphere sksph (radius 1.0) (material skymat))
(Sphere ssph (radius 1.0) (material skinmat))
(Sphere esph (radius 1.0) (material eyemat))
(Sphere psph (radius 1.0) (material pupilmat))
(Sphere scsph (radius 1.0) (material scalemat))

(Light sunlt
    (type 2) (color 1.39 1.2 1.0) (falloff 0) (deaddistance .01) (angularfalloff 25)
)

(Camera cam
    (perspective 1)
    (l -.334) (r .334) (b -.334) (t .334) (n 1) # no far plane 
)

(Light dir
    (type 0) (color .4 .8 1.2)
)

(Light amb
    (type 3) (color 1 1 1)
)

(G nostril
	(I n1 psph (S 0.25 2 1))
)

(G nose
	(I s1 ssph)
	(I n1 nostril (R -25 0 0 1) (R 30 1 0 0) (S 0.075 0.075 0.075) (T -0.9 0.35 0.3))
	(I n1 nostril (R -25 0 0 1) (R -30 1 0 0) (S 0.075 0.075 0.075) (T -0.9 0.35 -0.3))
)

(G eyebase
	(I s1 ssph (S 0.9 1.35 1))
	(I s2 esph (T -0.15 -.25 0.05) (S 0.9 1.25 1))
)

(G eye1
	(I eb eyebase (S 1 1 0.8))
	(I p1 psph (S 0.1 0.5 0.25)(T -1 -0.45 0) )
)


(G cheek
	(I g1 ssph (S 1.25 1.4 1.5))
	(I w1 esph (S 1.35 1.25 1.5)(T 0 -.25 0))
)

(G yface
	(I ns nose (S 2 2 2)(T -0.15 -0.8 -0.5))
	(I e1 eye1 (T 2 1.9 0.25))
	(I e2 eye1 (T 2 1.9 -1))
	(I c1 cheek (R 135 0 1 0) (S 2 1.25 1.25) (T 1.5 -0.55 -0.3))
	(I s1 scsph  (S 0.8 0.8 0.1) (R 50 0 0 1) (T 2 1.05 -0.5))
	(I s2 scsph  (S 0.8 0.8 0.1) (R 50 0 0 1) (T 2.5 0.65 -0.5))
	(I s3 scsph  (S 0.8 0.8 0.1) (R 50 0 0 1) (T 3 0.15 -0.5))
)

(G egg
	(I b1 esph (S 1 1.4 1))
	(I s1 ssph (S 0.05 0.5 0.4) (T -0.97 0 0))
	(I s2 ssph (S 0.05 0.5 0.4) (T 0.97 0 0))
	(I s3 ssph (S 0.4 0.5 0.05) (T 0 0 0.97))
	(I s4 ssph (S 0.4 0.5 0.05) (T 0 0 -0.97))
	(I s5 ssph (S 0.05 0.3 0.2)  (R 45 0 1 0) (R -35 0 0 1)(T -0.5 0.8 0.65))
	(I s6 ssph (S 0.05 0.3 0.2)  (R -45 0 1 0) (R 35 0 0 1)(T 0.5 0.8 0.65))
	(I s7 ssph (S 0.05 0.3 0.2)  (R 45 0 1 0) (R 35 0 0 1)(T -0.5 -0.8 0.65))
	(I s8 ssph (S 0.05 0.3 0.2)  (R -45 0 1 0) (R -35 0 0 1)(T 0.5 -0.8 0.65))
	(I s9 ssph (S 0.05 0.3 0.2)  (R -45 0 1 0) (R -35 0 0 1)(T -0.5 0.8 -0.65))
	(I s10 ssph (S 0.05 0.3 0.2)  (R 45 0 1 0) (R -35 0 0 1)(T 0.5 -0.8 -0.65))
	(I s11 ssph (S 0.05 0.3 0.2)  (R -45 0 1 0) (R 35 0 0 1)(T -0.5 -0.8 -0.65))
	(I s11 ssph (S 0.05 0.3 0.2)  (R 45 0 1 0) (R 35 0 0 1)(T 0.5 0.8 -0.65))
)

(G sceney
    (I cam1 cam)
    (I amb1 amb)
    (I sl sunlt (R -30 1 0 0)(T 0 5 -4))
    (I dir1 dir (Xform -.8165 0 -.5774 0
                           -.4082 -.7071 -.5774 0
                           -.4082 -.7071 .5774 0
                           0 0 0 1))
    (I sky sksph (S 2000 2000 .001) (T 0 0 -90))
    (I floor usph (S 1000 .001 1000) (T 0 -4 0))

	(I f1 yface (R 45 0 1 0)(T 4 0 -20))
	(I f2 yface (R 135 0 1 0)(T -3 0 -20))
	(I f3 yface (R 45 0 0 1) (R 90 0 1 0)(T 0.5 2 -25))
	(I e1 egg (S 1.75 1.75 1.75) (R 180 0 1 0) (T 0 -2 -19))
	(I e2 egg (S 1 1 1) (R -45 0 0 1) (R 45 0 1 0) (T 3.9 -2.5 -15))
	(I e3 egg (S 1 1 1) (R 25 1 0 0) (R 45 0 0 1) (R 45 0 1 0) (T -3.9 -3 -15))
	(I e4 egg (S 1 1 1) (R 86 1 0 0) (R 85 0 0 1) (R 85 0 1 0) (T -4 -3 -20))
	(I e5 egg (S 1 1 1) (R 36 1 0 0) (R 55 0 0 1) (R 23 0 1 0) (T 3.7 -2.8 -21))
	(I e7 egg (S 1 1 1) (R 232 1 0 0) (R 85 0 0 1) (R 132 0 1 0) (T 1 -3.3 -14))
	(I e7 egg (S 0.6 0.6 0.6) (R 132 1 0 0) (R 185 0 0 1) (R 182 0 1 0) (T -1.2 -2.3 -9))
)


(Render sceney)


