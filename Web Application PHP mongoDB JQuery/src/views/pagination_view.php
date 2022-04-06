<form action="view_gallery">
    <div id="nav">
        <a class = "paging_btn" href="view_gallery?page=<?= $page - 1 ?>">< <</a>
    <?php for($i=1;$i<11;$i++): ?>
        <a class="paging_btn" name="paging_btn" href='view_gallery?page=<?= $i ?>'><?= $i ?></a>
    <?php endfor ?>
        <a class = "paging_btn" href="view_gallery?page=<?= $page + 1 ?>">> ></a>
    </div>
</form>