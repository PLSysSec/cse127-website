serve:
	mkdocs serve
build:
	mkdocs build
publish: build
	-git add site && git commit -a -m "update site for publish"
	git subtree push --prefix=site origin site --squash 
	ssh dstefan@login.eng.ucsd.edu 'cd public_html/cse127-winter20/ && git fetch && git reset --hard origin/site'
remove:
	git push origin :site
install:
	sudo pip install mkdocs
	sudo pip install mkdocs-material
	sudo pip install mkdocs-include
