---
title: 'Code That Fits in Your Head'
subtitle: 'Heuristics for Software Engineering'
slug: 'code-that-fits-in-your-head'
date: '2021-11-24'
params:
  bookTitle: 'Code That Fits in Your Head'
  bookSubtitle: 'Heuristics for Software Engineering'
  bookGenre: Software Patterns & Practices
  bookAuthor: Mark Seemann
  bookPublishDate: '2021-11-15'
  bookCoverUrl: 'https://covers.openlibrary.org/b/id/12848531-L.jpg'
  bookPublisher:  Pearson Education
  bookReviewGrade: 3
---

First, note that I've read the "rough-cuts" version in the epub format. Any critique (or praise, for that matter) could have been adressed before the actual release.

The formatting bugged my e-reader quite a bit, but (as usual) this can be resolved by deleting most of the CSS file's content, especially the margins and paddings.

I'll start off by saying that I found the title to be a bit confusing. It does make sense after a few chapters, but I don't find it to be fitting for the book as a whole. I vaguely remember Mark saying in a podcast that the title wasn't his first choice, so I assume he had a better idea in mind.

I found the writing to be in line with the typical "Clean Code" style. The topics have an intended reading order but are also useful on their own, and are accompanied by various handy principles/patterns, stories, and a sample codebase.

Overall, I unfortunately must say that this book won't have a large impact on my work. This isn't because it doesn't include useful advice, but rather because I've already heard and adopted most of it in either exactly the same or a very similar way.

I e.g. write small "code" and run complexity analyzers anyway, thinking of it as a flower hierarchy won't have a large impact going forward. The fact that only small code fits in your head and you can explain that with psychology (2 minds of thinking by Kahnemann) is at best just another reason to write neat code, needless to say, that there are many more benefits.

I must applaud that Mark tried not to create new principles but to reason with existing material instead. Still, the book contains quite an amount of references to Robert C. Martin, as if everything you say must be true if you can link it to one of his statements (Not sure what I expected though, given that it was released in his series. So that's my bad, I guess).

I found the most value in the small things: E.g. to not assert the messages of exceptions, to write methods that intentionally fail tests to test the quality of the tests (devil's advocate), et cetera.

What the book definitely achieved is that I'm going to research some topics. E.g. until now it never came to my mind to do Code-Analysis based on git's history.

I also feel like this book gives me gunpowder to introduce new ideas to my team. While I already knew about property-based testing, just like most functional topics I have difficulties convincing comfy OO developers to give it a real try. If this is for the lack of coverage in "accepted" literature, I now can point to a Clean-Code series book for some techniques.

Conclusion: The book convinced me that it earns a place on my bookshelf, so I'm going to buy the paperback version soon. Unfortunately, I didn't quite feel like part of the target audience, so my review might not match others.

If you're reading this Mark: I would absolutely love to read a book in which you cover any functional topic to any target audience. Sure, the functional core / imperative shell and property-based testing chapters hinted at your interest in FP, but your blog makes it clear that you not only have a broad knowledge in this area but that you're able to translate it into practical scenarios too.
