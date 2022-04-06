<!DOCTYPE html>
<html>
<head>
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/gallery.css"/>
</head>

<body>

<a id ="back" href="postacie">Wróć do formularza</a>
<a id ="back" href="my_photos">Zobacz zapisane zdjęcia</a>


<form method="post" action="save_photos">
<div id="gallery">
    <?php if (!empty($photos)):
        $dirname = "static/images/upload/";
        include 'pagination_view.php'
        ?>
        <input id="remember" type="submit" value="Zapamiętaj wybrane"/>
        <?php foreach ($photos as $photo):
        $image = glob($dirname.'miniatures/'.$photo['author'].$photo['title'].'_miniature.'.$photo['ext']);
        ?>
        <div class="photo">
            <a target="_blank" href="<?= $dirname.'watermarked/'.$photo['author'].$photo['title'].'_watermarked.'.$photo['ext'] ?>">
            <?= '<img src="' ?>
            <?= $image[0] ?>
            <?= '"/>' ?>
            </a>
            <div style="clear:both"></div>
            <label name="saved_photo[]">Zapamiętaj: </label>
            <input type="checkbox" name="saved_photo[]" value="<?= $photo['author'].'#'.$photo['title'].'#'.$photo['ext'] ?>"/>
            <p><?= $photo['author'] ?></p>
            <p><?= $photo['title'] ?></p>
        </div>

    <?php endforeach ?>
    <?php endif ?>
</div>
</form>

</body>
</html>
