publish:
	-git commit -am "update site"
	-git push
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall21/ && git pull'
	cd ..  && git subtree split --prefix cse127-fall21 -b site-fa21 
	git push -f origin site-fa21:site-fa21
	git branch -D site-fa21
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-fall21/ && git fetch && git reset --hard origin/site-fa21'
remove:
	git push origin :site-fa21
