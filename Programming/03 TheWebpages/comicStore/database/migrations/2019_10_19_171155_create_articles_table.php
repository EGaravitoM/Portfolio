<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateArticlesTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('articles', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name_article');
            $table->mediumText('description_article');
            $table->boolean('active_article');
            $table->float('price', 10, 2);
            $table->float('rating',3,2)->nullable($value = true);
            $table->integer('units');
            $table->boolean('sale');
            $table->string('video');
            $table->integer('user_id')->unsingned();
            $table->timestamps();
        });
        DB::statement("ALTER TABLE articles ADD img1 mediumblob;");
        DB::statement("ALTER TABLE articles ADD img2 mediumblob;");
        DB::statement("ALTER TABLE articles ADD img3 mediumblob;");
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('articles');
    }
}
