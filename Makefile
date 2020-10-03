publish:
	-git commit -am "update site"
	-git push
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall20/ && git pull'
	cd ..  && git subtree split --prefix cse127-fall20 -b site 
	git push -f origin site:site
	git branch -D site
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall20/ && git fetch && git reset --hard origin/site'
remove:
	git push origin :site
