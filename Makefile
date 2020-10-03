publish:
	-git commit -am "update site"
	-git push
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall20/ && git pull'
	cd ..  && git subtree split --prefix cse127-fall20 -b site-fa20 
	git push -f origin site-fa20:site-fa20
	git branch -D site-fa20
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall20/ && git fetch && git reset --hard origin/site-fa20'
remove:
	git push origin :site-fa20
