<!DOCTYPE html>
<html>
<head>
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/gallery.css"/>
</head>

<body>

<a id ="back" href="postacie">Wróć do formularza</a>
<p id="saved_photos">Zapisane zdjęcia:</p>

<form method="post" action="save_photos">
    <div id="gallery">
        <?php if (!empty($photos)):
            $dirname = "static/images/upload/";
            include 'pagination_view.php'
            ?>
            <input id="remember" type="submit" value="Usuń zaznaczone"/>
            <?php foreach ($photos as $photo):
            $photo = explode('#',$photo);
            ?>
            <div class="photo">
                <a target="_blank" href="<?= $dirname.'watermarked/'.$photo[0].$photo[1].'_watermarked.'.$photo[2] ?>">
                    <?= '<img src="' ?>
                    <?= $dirname.'miniatures/'.$photo[0].$photo[1].'_miniature.'.$photo[2] ?>
                    <?= '"/>' ?>
                </a>
                <div style="clear:both"></div>
                <label name="saved_photo[]">Zapamiętaj: </label>
                <input type="checkbox" name="saved_photo[]" value="<?= $photo['author'].'#'.$photo['title'].'#'.$photo['ext']  ?>"/>
                <p><?= $photo[0] ?></p>
                <p><?= $photo[1] ?></p>
            </div>

        <?php endforeach ?>
        <?php endif ?>
    </div>
</form>

</body>
</html>
