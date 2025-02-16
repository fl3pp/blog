<script type="text/javascript">
document.addEventListener("DOMContentLoaded", (event) => {
    document.querySelectorAll('dl').forEach(dl => {
        const definitionList = document.createElement('div');
        definitionList.classList.add('definition-list');
        for (let i = 0; i < dl.children.length; i += 2) {
            const newDl = document.createElement('dl');
            newDl.append(dl.children[i].cloneNode(true), dl.children[i + 1].cloneNode(true));
            definitionList.appendChild(newDl);
        }
        dl.replaceWith(definitionList);
    })
});
</script>