<?php
/**
 * Add editor styles
 */
function base_add_editor_styles() {
  add_editor_style(get_stylesheet_directory_uri() . '/css/wysiwyg.css');
}
add_action('admin_init', 'base_add_editor_styles');

/**
 * WYSIWYG settings.
 */
function base_format_TinyMCE($in) {
  $in['accessibility_focus'] = true;
  $in['tabfocus_elements'] = 'major-publishing-actions';
  $in['block_formats'] = "Paragraph=p; Underrubrik=h2; Underrubrik nivå 2=h3";
  $in['toolbar1'] = 'bold,italic,bullist,numlist,blockquote,link,unlink,wp_more,spellchecker,wp_fullscreen,formatselect,pastetext,removeformat,undo,redo,wp_help ';
  $in['toolbar2'] = '';

  return $in;
}
add_filter('tiny_mce_before_init', 'base_format_TinyMCE');

/**
 * WYSIWYG image sizes.
 */
function base_custom_sizes( $sizes ) {
  $sizes = array(
    'wysiwyg_xsmall' => __('Small'),
    'wysiwyg_small' => __('Medium'),
    'wysiwyg' => __('Large'),
  );

  return $sizes;
}
add_filter( 'image_size_names_choose', 'base_custom_sizes' );

/**
 * WYSIWYG image markup.
 */
function base_img_caption_shortcode( $empty, $attr, $content ){
  $atts = shortcode_atts( array(
    'align'   => 'alignnone',
    'width'   => '',
    'caption' => '',
    'class'   => '',
    ), $attr, 'caption' );

  $atts['width'] = (int) $atts['width'];
  if ( $atts['width'] < 1 || empty( $atts['caption'] ) )
    return $content;

  $class = trim( 'c-media -' . $atts['align'] . ' ' . $atts['class'] );
  $width = $atts['width'];

  $caption_width = apply_filters( 'img_caption_shortcode_width', $width, $atts, $content );

  $html = '<figure class="' . esc_attr( $class ) . ' -caption">'
  . do_shortcode( $content ) . '<figcaption class="c-media__caption">' . $atts['caption'] . '</figcaption></figure>';

  return $html;
}
add_filter( 'img_caption_shortcode', 'base_img_caption_shortcode', 10, 3 );
