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


  if (isset($form['myapi_test'])) {
    $myapi_default = array();
    if (isset($node->myapi_test)) {
      $assoc_views_field = field_view_field('node', $node, 'myapi_test');
      $myapi_default = explode('+', $assoc_views_field['#items'][0]['value']);
    }

    //replace the created field for my own version
    $myapi_lang = $form['myapi_test']['#language'];
    $form['myapi_test'][$myapi_lang]['#type'] = 'select';
    $form['myapi_test'][$myapi_lang]['#multiple'] = TRUE;
    $form['myapi_test'][$myapi_lang]['#options'] = $view_names;
    $form['myapi_test'][$myapi_lang]['#default_value'] = $myapi_default;
    $form['myapi_test'][$myapi_lang]['#description'] = t('the views that this node will use');

    $form['view_data']['myapi_test'] = $form['myapi_test'];
    unset($form['myapi_test']);

  }

}


function myapi_node_submit($node, $form, &$form_state) {
  $lang = $form['language']['#value'];
  $combined = array();
  foreach($form_state['values']['myapi_test'][$lang] as $key) {
    $combined[] = $key['value'];
  }
  $combined = implode('+', $combined);
  //dpm($combined);
  $node->myapi_test[$lang] = array(
    0 => array (
      'value' => $combined
    )
  );

  dpm($node->myapi_test[$lang]);
}

// function myapi_field_attach_submit($entity_type, $entity, $form, &$form_state) {
//   dpm($form);
//   $lang = $form['language']['#value'];
//   $form_state['values']['myapi_test'][$lang][0]['value'] = 'changed!';
// }
