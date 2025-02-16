---
title: 'Unit Testing'
slug: 'unit-testing-principles-patterns-practices'
date: '2024-12-28'
params:
  bookTitle: 'Unit Testing'
  bookSubtitle:  'Principles, Practices, and Patterns'
  bookGenre: Software Patterns & Practices
  bookPublisher: Manning
  bookAuthor: Vladimir Khorikov 
  bookPublishDate: '2019-01-01'
  bookCoverUrl: 'https://covers.openlibrary.org/b/id/14572001-L.jpg'
  bookReviewGrade: 4
---

I was searching for a book that differentiates and clarifies different unit testing techniques because I felt like something was wrong with the approach I was taking up until this point.

I particularly wondered why test-driven development never really worked for me. It turns out that the most likely reason for this is because I was testing using the _London_ school of thought, and didn't know there was a _Detroit_ one as well [^1]. This clarification was tremendously valuable to me, as it finally explains what I have been missing. I really don't understand why other books that had a big influence on me in this regard, e.g., [The Art of Unit Testing](https://www.goodreads.com/book/show/17623611), didn't handle this topic at all. Even the ubiquitous [Clean Code](https://www.goodreads.com/book/show/3735293) seems to just assume a unit testing style. It may be because the London approach wasn't hugely popular at that time, at least it seems like the authors of the two examples are now aware of the distinction and have expressed their opinions publicly.

The book expands on the Detroit school of unit testing and does so really well. It goes beyond the basics of unit testing and expands on _what_ to test, and _when_ to test it. While doing so, the author reasons with well though out tools and examples, such as the four pillars of a good unit test.

However, it does assume that you are already familiar with the basics of testing, and also doesn't get into the details of how modern unit testing framework work. This makes it easy to adapt the learnings to ecosystems apart from .NET, but does not make the book very beginner-friendly.

I found everything I searched for in this book, but I still cannot give it a 5-star rating because of a few minor reasons:

- Chapter 7 touched upon the structure of programs, but didn't go into too much detail. I believe this topic belongs into the domain of software architecture, which should be treated more carefully and with other, more detailed material.

- At some points, the book felt a bit stretched, e.g., during the chapter 'Testing the database'. While I do see value in covering databases handling in tests, I felt like the book lost the focus on testing at some points. I got this feeling during other chapters as well.

However, these minor issues should not scare you away from this book. If you're a seasoned developer and are looking for ways to improve your testing approach, this book is absolutely for you.

[^1]: I don't want to state that test-driven development is impossible using the London school of thought, but it surely differs from TDD as explained in [Clean Code](https://www.goodreads.com/book/show/3735293) or [Test-Driven Development](https://www.goodreads.com/book/show/387190).