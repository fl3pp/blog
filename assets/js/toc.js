<script type="text/javascript">
document.addEventListener("DOMContentLoaded", (event) => {
  const main = document.querySelector(".main");
  const toc = document.querySelector(".table-of-contents");
  if (!main || !toc) return;
  const h1 = main.querySelector("h1");
  if (!h1) return;

  const tocYStart = h1.getBoundingClientRect().top; 
  document.querySelector('.table-of-contents-wrapper').style['padding-top'] = tocYStart.toString() + 'px';

  const headings = main.querySelectorAll("h2, h3");
  const tocList = document.createElement("ul");

  headings.forEach(heading => {
    const tocItem = document.createElement("li");
    tocItem.classList.add('toc-item-' + heading.tagName.toLowerCase());
    const tocLink = document.createElement("a");
    const headingText = heading.textContent;
    const headingId = headingText.toLowerCase().replace(/\s+/g, "-");

    // Set an id for the heading if it doesn't have one
    if (!heading.id) {
      heading.id = headingId;
    }

    tocLink.href = `#${heading.id}`;
    tocLink.textContent = headingText;
    tocItem.appendChild(tocLink);
    tocList.appendChild(tocItem);
  });

  toc.appendChild(tocList);
});
</script>