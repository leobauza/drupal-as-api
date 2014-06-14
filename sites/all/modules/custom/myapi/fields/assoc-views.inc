<?php
/**
 * Implements hook_form_FORM_ID_alter().
 */
function myapi_form_node_form_alter(&$form, $form_state, $form_id) {
  $views = views_get_all_views();
  $view_names = array(
    0 => t('none')
  );
  foreach ($views as $view) {
    $view_names[$view->name] = t($view->name);
  }

  $node = $form['#node'];
  //dpm($node);
  $nid = $node->nid;

  $form['data_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99
  );

  $form['view_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('View Data'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // '#group' => 'additional_settings',
    '#group' => 'data_settings',
    '#weight' => 100,
  );


  if (isset($form['assoc_views'])) {
    $myapi_default = array();
    if (isset($node->assoc_views)) {
      $assoc_views_field = field_view_field('node', $node, 'assoc_views');
      if (isset($assoc_views_field['#items'][0]['value'])) {
        $myapi_default = explode('+', $assoc_views_field['#items'][0]['value']);
      }
    }

    //replace the created field for my own version
    $myapi_lang = $form['assoc_views']['#language'];
    $form['assoc_views'][$myapi_lang]['#type'] = 'select';
    $form['assoc_views'][$myapi_lang]['#multiple'] = TRUE;
    $form['assoc_views'][$myapi_lang]['#options'] = $view_names;
    $form['assoc_views'][$myapi_lang]['#default_value'] = $myapi_default;
    $form['assoc_views'][$myapi_lang]['#description'] = t('the views that this node will use');

    $form['view_data']['assoc_views'] = $form['assoc_views'];
    unset($form['assoc_views']);

  }

}


function myapi_node_submit($node, $form, &$form_state) {
  $lang = $form['language']['#value'];
  $combined = array();
  foreach($form_state['values']['assoc_views'][$lang] as $key) {
    $combined[] = $key['value'];
  }
  $combined = implode('+', $combined);
  //dpm($combined);
  $node->assoc_views[$lang] = array(
    0 => array (
      'value' => $combined
    )
  );

  dpm($node->assoc_views[$lang]);
}

// function myapi_field_attach_submit($entity_type, $entity, $form, &$form_state) {
//   dpm($form);
//   $lang = $form['language']['#value'];
//   $form_state['values']['assoc_views'][$lang][0]['value'] = 'changed!';
// }
