# Assignment 5 *100pts*

**Deadline: Wednesday, November 20, 2019 by 1:59:59 PM**

**Early Turn-In: Sunday, November 17, 2019 by 11:59:59 PM (10% bonus)**

## Introduction

A talented but, unfortunately, clumsy student in Deian's research group accidentally dropped a flash drive in the campus coffee shop.  You, an infamously nefarious hacker known far and wide as the archvillain of the research group, noticed this dropped flash drive, and quickly but surreptitiously pocketed it.  As usual, you're trying to do everything in your power to disrupt all of the activities of the research group. Your latest scheme requires you to get control of the account Deian uses to access campus networks, and you have a sneaking suspicion that this dropped flash drive might be just the foothold you need in order to set your scheme in motion.

Being a smart but cautious hacker, you connected the flash drive to a secure, isolated machine to inspect its contents.  You don't want a repeat of that one time when a similar dropped flash drive actually contained a nasty virus and you ended up having to wipe your machine and reinstall your operating system.  But this one seems to have nothing suspicious, no traps or hidden surprises.  This drop seems to actually have been an accident.  Feeling exhilarated, you quickly email a dump of the flash drive's contents to yourself so you can access it on your primary machine.

Unfortunately, a quick glance shows that there's not much of interest on this flash drive itself.  You were hoping it might have something juicy, like the plans for the research group's next super-potent virus.  But all is not lost.  You might still be able to use some of the information on this flash drive to breach into the research group's super-secret network.  And then who knows what information you might be able to find just by listening in to what's going on...

## Logistics and Opening Hints

You should have already received the "email to yourself" with the dump of the dropped flash drive's contents.  That should be all you need to get started - what interesting things might be here that would prove useful for your hacking activities?

You'll eventually have to turn in a writeup describing the steps you took to achieve your goals, so you may want to keep a log as you go in order to make that easier.

Linux commands you may need to know about or look up for this assignment, in alphabetical order, include:
- `nc`
- `nmap`
- `ssh`
- `tcpdump`
- `wget`

Certain flags of some of these commands may also come in useful, such as `-F`, `-i`, `-p`, and `-X`, among others. Information can be found on man pages (e.g., `man nc`) or online.

---

We hope this assignment will be enjoyable and interesting for you.  In order to preserve the experience for everyone, please be careful with spoilers on Piazza and in class - part of the fun is finding the relevant information and figuring out how you're supposed to use it.  As usual, the TA's will be available in office hours and via private questions on Piazza to provide help and maybe some hints if necessary.

Also, once you breach into the network, you should be able to find a `README.md` file in the victim's home directory with additional directions and hints for the next steps.

Good luck in your hacking!
