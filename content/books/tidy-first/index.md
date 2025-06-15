---
title: 'Tidy First?'
subtitle: 'A Personal Exercise in Empirical Software Design'
slug: 'tidy-first'
date: '2025-06-13'
params:
  bookTitle: 'Tidy First?'
  bookSubtitle: 'A Personal Exercise in Empirical Software Design'
  bookGenre: Software Patterns & Practices
  bookPublisher: O'Reilly Media
  bookAuthor: Kent Beck 
  bookPublishDate: '2023-10-01'
  bookCoverUrl: 'https://covers.openlibrary.org/b/id/14551145-L.jpg'
  bookReviewGrade: 3
---

I'm not quite sure what to think of this one. The book is quite short and can be divided into two parts:

The **first** part consists of a few 'tidying', which really are tiny refactorings. The idea is that you shouldn't start big refactorings, but improve code little by little. The upside with this approach is that you don't need to plan it, and that the risk of going into an unfortunate direction remains minimal for each step.

The **second** part consists of a theory where, in essence, the author argues about whether and when you should apply the 'tidyings':

- On one side, you can say that you should never take time for tidying because of 'discounted money': Investments into the future may or may not eventually pay, and in theory, the investment is thus worth less because of that uncertainty. Especially if you can instead invest in guaranteed short-term opportunities, e.g., features.
- The other side says that a cleaner structure can provide opportunities, also 'options', down the road. Just like with options in the trade market, they often cost very little if they're bought early enough, and may be worth a lot in the future. For example, a new feature may become significantly easier to implement because some refactoring investment had been made in the past. It is, however, just like with options in the stock market, not known beforehand whether they may ultimately pay out. If it works out, though, the gains can become significant.
 
The rest of the book goes into more detail and weights the two options, answering the question 'Tidy first?', or, whether to tidy or not (and whether to do it first, but other times such as 'later' are discussed as well). There is, of course, a lot more detail and examples of when the decision is a clear-cut and when it isn't.

I, personally, am unsure what to make of this theory. It certainly has a point, but I disagree in some situations:

- In my opinion, you sometimes don't get around big refactorings (a Win32 application cannot be simply ported to the web through 'tidyings', and neither can a COBOL application), which the author almost discounts entirely.

- I don't see why 'tidying's shouldn't be tracked. It should surely be possible for developers to improve the code without checking back with the PO or similar every time, but it is likely also not right to disregard their opinion entirely. Especially if it takes a good chunk out of the development resources. Small tasks do pile up.<

- The biggest potential 'options' are, in my opinion, opened with changes at an architectural level. None of the mentioned 'tidyings' provide guidance for such higher-level investments. But I agree with the author in that they are the most risky.

For experienced developers, the first part about 'tidying' is not going to contain anything new, or even interesting. The second part is nice to think about, but as I mentioned previously, in my very personal opinion, not without some flaws (your opinions may vary.).

Fresh developers could profit from the first 'tidyings' part of the book, but are probably not going to be able to relate too much to the second part.

So I'm not sure whom to recommend this book to.

The author also mentioned that this book is only the first of a series, related to the things that a single developer can do (small 'tidyings'). Maybe my points will be cleared by a future release.